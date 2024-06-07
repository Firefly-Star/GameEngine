#pragma once

#include "Core/Core.h"
#include "TypeStruct.h"

namespace FireFly
{
	//------------ParamPacker-------------

	class ParamPacker
	{
	public:
		// 10kB Buffer
#define FF_PARAMPACKER_BUFFER_SIZE 10 * 1024
		ParamPacker()
			:m_Alignment(1)
		{
			m_Buffer = new byte[FF_PARAMPACKER_BUFFER_SIZE];
			m_BufferWorkPtr = m_Buffer;
		}
		~ParamPacker()
		{
			if (m_Buffer)
			{
				delete[]m_Buffer;
			}
			m_Buffer = nullptr;
			m_BufferWorkPtr = nullptr;
		}

		template<typename... Ts>
		void Pack(const Ts&... params)
		{
			if constexpr (sizeof...(Ts) > 0)
			{
				PackImpl<Ts...>(params...);
			}
		}
		inline byte* GetBuffer() { return m_Buffer; }
		inline size_t GetSize() { return m_BufferWorkPtr - m_Buffer; }
		inline unsigned int GetAlignment() { return m_Alignment; }
	private:
		template<typename T, typename... Ts>
		void PackImpl(const T& param, const Ts&... params)
		{
			unsigned int alignment = alignof(T);
			if (alignment > m_Alignment)
			{
				m_Alignment = alignment;
			}
			unsigned int offset = (size_t)m_BufferWorkPtr % alignment;
			if (offset != 0)
			{
				m_BufferWorkPtr += alignment - offset;
			}
			FF_CORE_ASSERT((m_BufferWorkPtr - m_Buffer + sizeof(T)) <= FF_PARAMPACKER_BUFFER_SIZE, "ParamPacker memory overflow!");

			*(T*)m_BufferWorkPtr = param;
			m_BufferWorkPtr += sizeof(T);
			if constexpr (sizeof...(Ts) > 0)
			{
				PackImpl<Ts...>(params...);
			}
		}
	private:
		byte* m_Buffer;
		byte* m_BufferWorkPtr;
		unsigned int m_Alignment;
	};

	template<typename... Ts>
	static ParamPacker CreateParamPacker(const Ts&... params)
	{
		ParamPacker p;
		p.Pack(params...);
		return p;
	}

	//-----------ParamUnPacker------------
	template<typename ... Ts>
	class ParamUnPacker
	{
	public:
		ParamUnPacker(byte* parampack, TypeList<Ts...> typelist)
			:m_Buffer(parampack), m_WorkPtr(parampack), m_Params()
		{
		}
		void UnPack()
		{
			UnPackImpl<0>();
		}
		inline std::tuple<Ts...> GetParams() { return m_Params; }
		inline void SetBuffer(byte* buffer) { m_Buffer = buffer; m_WorkPtr = buffer; }
	private:
		template<size_t Index>
		void UnPackImpl()
		{
			if constexpr (Index < sizeof...(Ts))
			{
				using type = typename TypeList<Ts...>::type<Index>;
				unsigned int alignment = alignof(type);
				unsigned int offset = (size_t)m_WorkPtr % alignment;
				if (offset != 0)
				{
					m_WorkPtr += alignment - offset;
				}
				type value = *(type*)m_WorkPtr;
				std::get<Index>(m_Params) = value;
				m_WorkPtr += sizeof(type);
				UnPackImpl<Index + 1>();
			}
		}
	private:
		byte* m_Buffer;
		byte* m_WorkPtr;
		std::tuple<Ts...> m_Params;
	};

	//-----------ParamTool-----------
	template<typename... Ts>
	class ParamTool
	{
	public:
		ParamTool(const Ts&... params)
			:m_UnPacker(nullptr, ParamsToTypeList(params...)), m_Packer()
		{
			m_Packer.Pack(params...);
		}
	protected:
		ParamPacker m_Packer;
		ParamUnPacker<Ts...> m_UnPacker;
	};
}

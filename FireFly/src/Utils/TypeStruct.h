#pragma once
namespace FireFly
{
	//------------TypeAtIndex---------------

	template<unsigned int Index, typename T, typename... Ts>
	struct TypeAtIndex
	{
		using type = typename TypeAtIndex<Index - 1, Ts...>::type;
	};

	template<typename T, typename... Ts>
	struct TypeAtIndex<0, T, Ts...>
	{
		using type = T;
	};

	//-------------TypeStruct---------------
	template<typename... Ts>
	struct TypeList
	{
		template<unsigned int Index>
		using type = typename TypeAtIndex<Index, Ts...>::type;
		unsigned int static GetSize()
		{
			return sizeof...(Ts);
		}
	};

	template<>
	struct TypeList<>
	{
		struct NoType{};
		template<unsigned int Index>
		using type = NoType;
	};

	template<typename... Ts>
	TypeList<Ts...> ParamsToTypeList(const Ts&... params)
	{
		return TypeList<Ts...>();
	}


}
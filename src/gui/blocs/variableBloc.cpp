#include "variableBloc.hpp"

satap::VariableBloc::VariableBloc(State::Context context) :
	Bloc(context, VariableBlocType),
	VariableModel() {}

satap::VariableBloc::VariableBloc(State::Context context, std::string name, sct_type value) :
	Bloc(context, VariableBlocType),
	VariableModel(name, value) {}

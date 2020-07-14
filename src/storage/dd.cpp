#include "dd.h"
#include "storm/storage/dd/DdManager.h"
#include "storm/storage/dd/Dd.h"
#include "storm/storage/dd/Bdd.h"
#include "src/helpers.h"

template<storm::dd::DdType DdType>
void define_dd(py::module& m, std::string const& libstring) {
    py::class_<storm::dd::DdMetaVariable<DdType>> ddMetaVariable(m, (std::string("DdMetaVariable_") + libstring).c_str());
    ddMetaVariable.def("compute_indices", &storm::dd::DdMetaVariable<DdType>::getIndices, py::arg("sorted")=true);
    ddMetaVariable.def_property_readonly("name", &storm::dd::DdMetaVariable<DdType>::getName);

    py::class_<storm::dd::DdManager<DdType>, std::shared_ptr<storm::dd::DdManager<DdType>>> ddManager(m, (std::string("DdManager_") + libstring).c_str());
    //ddManager.def("get_meta_variable", &storm::dd::DdManager<DdType>::getMetaVariable, py::arg("expression_variable"));

    py::class_<storm::dd::Dd<DdType>> dd(m, (std::string("Dd_") + libstring).c_str(), "Dd");
    dd.def_property_readonly("node_count", &storm::dd::Dd<DdType>::getNodeCount, "get node count");
    dd.def_property_readonly("dd_manager", &storm::dd::Dd<DdType>::getDdManager, "get the manager");
    dd.def_property_readonly("meta_variables", [](storm::dd::Dd<DdType> const& dd) {return dd.getContainedMetaVariables();}, "the contained meta variables");


    py::class_<storm::dd::Bdd<DdType>> bdd(m, (std::string("Bdd_") + libstring).c_str(), "Bdd", dd);
    bdd.def("to_expression", &storm::dd::Bdd<DdType>::toExpression, py::arg("expression_manager"));
}


template void define_dd<storm::dd::DdType::Sylvan>(py::module& m, std::string const& libstring);
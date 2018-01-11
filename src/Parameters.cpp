#include <iostream>
#include "Parameters.h"

using namespace boost;

Parameters::Input::
Input():
  tree(""),
  first_event(0),
  last_event(-1)
{
}

Parameters::Output::
Output():
  output_file(""),
  output_tree("")
{
}

Parameters::Signal::
Signal():
  hit_selection_type("")
{
}

Parameters::Mixing::
Mixing():
  random_seed(1234)
{
}

Parameters::Geometry::
Geometry():
  panel_mapping_file("")
{
}

Parameters::
Parameters()
{
}

void
Parameters::
read(const std::string& file)
{
  Py_Initialize();
  python::object main_module = python::import("__main__");
  python::dict main_namespace = python::extract<python::dict>(main_module.attr("__dict__"));
  python::object py_module = python::exec_file(file.c_str(), main_namespace);
  fillInput(main_namespace);
  fillOutput(main_namespace);
  fillMixing(main_namespace);
  fillSignal(main_namespace);
  fillGeometry(main_namespace);
}


void 
Parameters::
fillInput(const python::dict& dict)
{
  python::list signal_files = python::extract<python::list>(dict["input_signal"]);
  python::list signal_files_0pu = python::extract<python::list>(dict["input_signal_0pu"]);
  python::list background_files = python::extract<python::list>(dict["input_background"]);
  input_.signal_files = toStdVector<std::string>(signal_files);
  input_.signal_files_0pu = toStdVector<std::string>(signal_files_0pu);
  input_.background_files = toStdVector<std::string>(background_files);
  input_.tree = python::extract<std::string>(dict["input_tree"]);
  input_.first_event = python::extract<int>(dict["input_first_event"]);
  input_.last_event = python::extract<int>(dict["input_last_event"]);
}

void 
Parameters::
fillOutput(const python::dict& dict)
{
  output_.output_file = python::extract<std::string>(dict["output_file"]);
  output_.output_tree = python::extract<std::string>(dict["output_tree"]);
}

void 
Parameters::
fillMixing(const python::dict& dict)
{
  mixing_.random_seed = python::extract<unsigned>(dict["mixing_random_seed"]);
  python::list bunch_pattern = python::extract<python::list>(dict["bunch_pattern"]);
  mixing_.bunch_pattern = toStdVector<unsigned>(bunch_pattern);
}

void 
Parameters::
fillSignal(const python::dict& dict)
{
  signal_.hit_selection_type = python::extract<std::string>(dict["signal_hit_selection_type"]);
  python::dict hit_selection_parameters = python::extract<python::dict>(dict["signal_hit_selection_parameters"]);
  signal_.hit_selection_parameters = toStdMap<std::string,float>(hit_selection_parameters);
}

void 
Parameters::
fillGeometry(const python::dict& dict)
{
  geometry_.panel_mapping_file = python::extract<std::string>(dict["panel_mapping"]);
}


void
Parameters::
print() const
{
  std::cout<<"|Configuration parameters\n";
  std::cout<<"|- Inputs\n";
  std::cout<<"|-- Signal = \n";
  for(const auto& file : input_.signal_files)
  {
    std::cout<<"|    "<<file<<"\n";
  }
  std::cout<<"|-- Signal 0PU = \n";
  for(const auto& file : input_.signal_files_0pu)
  {
    std::cout<<"|   "<<file<<"\n";
  }
  std::cout<<"|-- Background = \n";
  for(const auto& file : input_.background_files)
  {
    std::cout<<"|   "<<file<<"\n";
  }
  std::cout<<"|-- Tree = "<<input_.tree<<"\n";
  std::cout<<"|-- Events = ["<<input_.first_event<<","<<input_.last_event<<"]\n";
  std::cout<<"|- Output\n";
  std::cout<<"|-- File = "<<output_.output_file<<"\n";
  std::cout<<"|-- Tree = "<<output_.output_tree<<"\n";
  std::cout<<"|- Signal\n";
  std::cout<<"|-- Hit selection type = "<<signal_.hit_selection_type<<"\n";
  std::cout<<"|-- Hit selection parameters  = {\n";
  for(const auto& pars : signal_.hit_selection_parameters)
  {
    std::cout<<"|-- "<<pars.first<<" : "<<pars.second<<"\n";
  }
  std::cout<<"|-- }\n";
  std::cout<<"|- Mixing\n";
  std::cout<<"|-- Random seed = "<<mixing_.random_seed<<"\n";
  std::cout<<"|-- Bunch pattern = [";
  for(const auto& bx : mixing_.bunch_pattern)
  {
    std::cout<<bx<<" ";
  }
  std::cout<<"]\n";
  std::cout<<"|- Geometry\n";
  std::cout<<"|-- Panel mapping = "<<geometry_.panel_mapping_file<<"\n";
}

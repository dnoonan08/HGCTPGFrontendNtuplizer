#include <iostream>
#include <string>

#include "HGCTPG/FrontendNtuplizer/interface/Parameters.h"
#include "HGCTPG/FrontendNtuplizer/interface/Manager.h"


int main(int argc, char** argv) 
{

  if(argc!=2)
  {
    std::cout<<"Usage:\n";
    std::cout<<" shower_simulation.exe config_file_name.py\n";
    return 1;
  }

  std::string config_file(argv[1]);
  Parameters params;
  try
  {
    params.read(config_file);
    params.print();
  }
  catch(const std::string& excep)
  {
    std::cout<<"An error occured while reading the python config file:\n";
    std::cout<<excep<<"\n";
    return 2;
  }
  catch(const boost::python::error_already_set& excep)
  {
    std::cout<<"An error occured while reading the python config file:\n";
    PyErr_Print();
    PyErr_Clear();
    return 2;
  }
  catch(...)
  {
    std::cout<<"An undefined error occured while reading the python config file\n";
    return 2;
  }

  try
  {
    Manager manager(params);
    manager.run();
  }
  catch(const std::string& excep)
  {
    std::cout<<"An error occured:\n";
    std::cout<<excep<<"\n";
    return 3;
  }
  catch(const std::exception& excep)
  {
    std::cout<<"An error occured:\n";
    std::cout<<excep.what()<<"\n";
    return 3;
  }
  return 0;
}

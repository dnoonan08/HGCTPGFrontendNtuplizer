#ifndef __HGCTPG_FrontendNtuplizer_Parameters_h__
#define __HGCTPG_FrontendNtuplizer_Parameters_h__

#include <vector>
#include <map>
#include <string>
#include <boost/python.hpp>
#include <boost/python/object.hpp>
#include <boost/python/stl_iterator.hpp>

class Parameters
{
  public:
    struct Input
    {
      Input();
      std::vector<std::string> signal_files;
      std::vector<std::string> signal_files_0pu;
      std::vector<std::string> background_files;
      std::string tree;
      int first_event;
      int last_event;
    };

    struct Output
    {
      Output();
      std::string output_file;
      std::string output_tree;
    };

    struct Signal 
    {
      Signal();
      std::string hit_selection_type;
      std::map<std::string,float> hit_selection_parameters;
    };

    struct Mixing 
    {
      Mixing();
      unsigned random_seed;
      std::vector<unsigned> bunch_pattern;
    };

    struct Geometry
    {
      Geometry();
      std::string panel_mapping_file;
    };


  public:
    Parameters();
    ~Parameters() {};

    void read(const std::string&);
    void print() const;

    const Input& input() const {return input_;}
    const Output& output() const {return output_;}
    const Mixing& mixing() const {return mixing_;}
    const Signal& signal() const {return signal_;}
    const Geometry& geometry() const {return geometry_;}

  private:
    void fillInput(const boost::python::dict& dict);
    void fillOutput(const boost::python::dict& dict);
    void fillMixing(const boost::python::dict& dict);
    void fillSignal(const boost::python::dict& dict);
    void fillGeometry(const boost::python::dict& dict);

    // Converters to std objects
    template<typename T>
    std::vector<T>
    toStdVector(const boost::python::list& plist)
    {
      boost::python::stl_input_iterator<T> begin(plist), end;
      return std::vector<T>(begin,end);
    }
    template<typename Key, typename Value>
    std::map<Key,Value>
    toStdMap(const boost::python::dict& pdict)
    {
      std::map<Key, Value> output;
      boost::python::list keys = pdict.keys();
      for(unsigned i=0; i<len(keys);++i)
      {
        Key key = boost::python::extract<Key>(keys[i]);
        Value value = boost::python::extract<Value>(pdict[key]);
        output.emplace(key, value);
      }
      return output;
    }


    Input input_;
    Output output_;
    Mixing mixing_;
    Signal signal_;
    Geometry geometry_;
};

#endif

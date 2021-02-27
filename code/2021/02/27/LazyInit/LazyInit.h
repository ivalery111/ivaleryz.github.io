#include <functional>
#include <optional>

namespace lazy {

using std::function;
using std::optional;


template <typename T> class LazyInit {
public:
  explicit LazyInit(function<T()> init);

  bool HasValue() const;
  const T& Get() const;

private:
    function<T()> init_;
  mutable optional<T> value_;
};

template <typename T>
LazyInit<T>::LazyInit(function<T()> init) : init_(std::move(init)) {}

template <typename T>
bool LazyInit<T>::HasValue() const {
  return value_.has_value();
}

template <typename T>
const T& LazyInit<T>::Get() const{
  if(!value_){
    value_ = init_();
  }
  return *value_;
}

} // namespace lazy
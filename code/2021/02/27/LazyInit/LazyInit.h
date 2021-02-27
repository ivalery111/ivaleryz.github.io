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

} // namespace lazy
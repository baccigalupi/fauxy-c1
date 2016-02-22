#include "native_registry.h"
#include "object.h"

FxI_NativeFunction FxI_NativeRegistry_add(FxI_NativeRegistry *registry, char *key, FxI_NativeFunction value) {
  fxb_hash_map_set(registry, key, value); // TODO: verification of set?, hash map returns integer status
  return value;
}

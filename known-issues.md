# Known Issues
--------

There are somethings that are problems that are on hold in favor of an MVP for the language:

* _Large Floating Points (and other numbers)_: Currently the assignment of numbers to numeric bit values is wonky. There hasn't been enough investment in converting strings of numbers into the appropriate sized memory slot. The language goal is that there are very frequently small numbers in use, but when a number gets larger precision matters and as much space as possible should be allocated. Current implementation
  * Fails to allocate correctly for large floats
  * When inspecting those float will memory overrun

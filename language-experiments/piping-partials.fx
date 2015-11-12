a(x) >> b(:foo, _.value) >> c(_, 'bar')

DataParser.new(data) >> DbRecord.new(_).create

// syntax for unbinding
// do we need to unbind, or is just rebind

it("should assert truth") -> {
  assert(true)
}.unbind

it("should assert truth") -> {
  assert(true)
} --

it("should assert truth") ~> {
  assert(true)
}

it("should assert truth") {
  assert(true)
}

it("should assert truth") ->> {
  assert(true)
}

// syntax for rebinding

f.bind(object)

f << object

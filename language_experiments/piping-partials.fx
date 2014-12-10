a(x) >> b(_)

DataParser.new(data) >> DbRecord.new(_).create

// syntax for unbinding

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

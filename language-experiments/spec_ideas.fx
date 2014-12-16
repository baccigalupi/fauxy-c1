/*
  Lessons learned:

  File scoping:
  `export` is necessary for things like specs, probably for other functionality
  therefore `import`
  makes sense of local variable scope for files

  Block Binding:
  At top level in file, are anonymous
  Anonymous get bound when called

  Block :run, classes can act like blocks with define run methods!

  also think precedence around 'import', 'export' keywords
  && and || or == !== === should be called out in lexer for precedence

  delegate_to method on classes

  Questions:

  MyClass: Class.new -> {}

  Block.new my_block
  Pass block with &block and call automatically
  Or call with .run or parens

  File objects have the require and import objects

*/

Spec(description, block) -> {
  setup: -> {
    results: List.new
  }

  run: -> {
    block.run
  }

  assert: -> (value) {
    results.add(value.to_boolean)
  }

  failure-count: -> {
    results.count -> (boolean) { !boolean }
  }

  success?: -> {
    results.count > 1 && failure-count == 0
  }
}

//------------------------

Spec.Describe(description) -> {
  init: ->(description, block: Block) {
    init(description)
    block.run
  }

  seutp: ->() {
    specs: List.new
  }

  it: -> (description, block) {
    specs.add( Spec.new(description, &block) )
  }

  run: -> {
    each -> (s) { s.run }
  }

  delegate_to(:specs, (:map, :each))
}

// ------------------------

Spec.FileRunner(directory, pattern) -> {
  init: -> {
    init(Dir.new, "*_spec.fx")
  }

  files: -> {

  }

  import-all -> {
    files.map -> (f) { f.import }
  }

  run -> {
    Spec.Runner.new(import-all)
  }

  report -> {
    report(DefaultReporter)
  }

  report -> (reporter_class) {
    run.map -> (spec) { reporter_class.new(spec).report }
  }
}

// -------------

Spec.Runner(specs) -> {
  run: -> {
    specs.map -> (spec) {
      run(spec)
    }.flatten
  }

  run: -> (describe: Describe) -> {
    describe.map -> (s) { run(s) }
  }

  run: -> (spec: Spec) -> {
    spec.run
  }
}

// ------------

Spec.DefaultReporter(spec) -> {
  report: -> {
    report(spec.status, spec.description)
  }

  report: -> (status: true, description) {
    Console.print-line("Passed: {{description}}", :green)
  }

  report: -> (status: false, description) {
    Console.print-line("Failed: {{description}}", :red)
  }
}

// -------------

Spec.HtmlReporter << Spec.DefaultReporter -> {
  report: -> (status: true, description) {
    "<span class='success'>{{description}}</span>"
  }

  report: -> (status: false, description) {
    "<span class='failure'>{{description}}</span>"
  }
}

//--------------------------

// initializes with a string and a block
describe = Spec.Describe.new("Spec Class")
describe.it("it should assert truth") -> { assert(true) }
describe.it("it should understand failure") -> { assert(false) }
export describe

// -------------------------

export Spec.Describe.new("Spec Class") -> {
  it("should assert truth") -> (s) {
    s.assert(1 == 1, "expected equal")
  }

  it("should understand failure") -> (s) {
    s.assert(true)
  }

  // Syntax for unbinding ???

  it("should assert truth") -> {
    assert(true)
  }.unbind

  it("should assert truth") -> {
    assert(true)
  }-

  it("should assert truth") ~> {
    assert(true)
  }

  it("should assert truth") {
    assert(true)
  }

  it("should assert truth") _> {
    assert(true)
  }


  // ------------
}

// -------------------------

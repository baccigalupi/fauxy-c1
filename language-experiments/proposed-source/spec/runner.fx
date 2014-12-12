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

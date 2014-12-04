/*
  Currently this is based on assert doing true/false returns
  rather than raising errors.
  Raising errors have the benefit of getting a stack trace
  That implies we want to have an ability to get a trace from wherever we are
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

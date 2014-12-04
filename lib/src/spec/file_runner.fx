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
    report(Spec.Reporter)
  }

  report -> (reporter_class) {
    run.map -> (spec) { reporter_class.new(spec).report }
  }
}

Spec.Reporter(spec) -> {
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

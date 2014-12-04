Spec.Reporter.HTML << Spec.DefaultReporter -> {
  report: -> (status: true, description) {
    "<span class='success'>{{description}}</span>"
  }

  report: -> (status: false, description) {
    "<span class='failure'>{{description}}</span>"
  }
}

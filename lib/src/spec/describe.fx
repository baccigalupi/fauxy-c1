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

  delegate_to(:specs, :map, :each)
}

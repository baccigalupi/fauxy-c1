/*
  .class allows a method call which will make more sense in the system ??

*/

Stream: class(callbacks) -> {
  init: -> {
    init(List.new)
  }

  on: -> (name, block) {
    add-callback(name, block)
  }

  add: -> (object) {
    trigger(:add, object)
  }

  alias(:<<, to: :add)

  // ---------
  trigger: -> (name, object) {
    callbacks-for.each -> (callback) {
      callback.run(object)
    }
  }

  add-callback: -> (name, block) {
    callbacks << Callback.new(name, block)
  }

  callbacks-for: -> (name) {
    callbacks // In base class, only add events and callbacks
  }
}

Stream.Accumulating.class(objects, callbacks) << Stream -> {
  init: -> {
    objects: List.new
    super
  }

  init: -> (objects) {
    objects: objects
    init
  }

  on: -> (name, block) {
    add-callback(name, block)
    self
  }

  on: -> (name: name == :add, block) {
    // handles object already in the objects
    objects.each -> (object) { block.run(object) }
    add-callback(name, block)
    self
  }

  finish: -> (object) {
    objects.freeze
    trigger(:finish, object)
  }

  finish: -> {
    finish(:finish, nil)
  }
}

Stream.Callback.class(name, block) -> {
  delegate_to(:block, :run)
}

// ------

stream = Stream.new
stream.on(:add) -> (object) { Console.pl object } // pl == print-line, p == print
stream << "something"

// "something"
// ------

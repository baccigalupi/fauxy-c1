Stream: Class.new(:transformer) -> {
  init: -> (class: Class) {
    transformer: -> (object) { class.new(object) }
  }

  // http://mudge.name/2014/11/26/data-structures-as-functions.html?utm_source=rubyweekly&utm_medium=email
  add: -> (object) {
    transformer.run(object) // could also be transform.run(object)
  }

  alias(:<<, to: :add)
}

// Stream.new(MyClass) // MyClass.new // calls run on add
// Stream.new -> (arg) { Console.print-line arg }
// stream = Stream.new(MyClass)
// stream.add "foo"

// creating your own if case

if: ->(condition: !!condition == true, block) {
  block.run
}

if: ->(condition, block) {
  // no op
}

if (something) -> { do-something }

if: -> (condition: !!condition == true, true-case, false-case) {
  true-case.run
}

if: -> (condition: !!condition == true, true-case, false-case) {
  false-case.run
}

if (something) -> {
  // true case
} -> {
  // false case
}



else: -> (block) {

}


// This kind of a stream is like each, requires side effects, unless we pass in a curried
// function, maybe
Stream.new -> (data) {
  DataParser.new(data) >> DbRecord.create(_)
}

// If we call an object like a function .. it runs the 'run' method ??
// Or just do the simpler thing like this? and the init above
Stream.new(RecordWriter)

Stream.Accumulating: Stream.inherit -> {
  setup: -> {
    actor: true
    collection: List.new
  }

  add: -> (object) {
    collection << super
    self
  }

  join: -> (reducer) {
    // something here to wait for concurrency ??
    reducer.run(list)
  }
}

describer = Stream.Accumulating.new -> (n) {
  Hundreds.new(n).to-words
}

describer << 234 << 20 << 1
describer.join -> (list) { list.reverse.join(' ') }

// Stream: class(callbacks) -> {
//   init: -> {
//     init(List.new)
//   }
//
//   on: -> (name, block) {
//     add-callback(name, block)
//   }
//
//   add: -> (object) {
//     trigger(:add, object)
//   }
//
//   alias(:<<, to: :add)
//
//   // ---------
//   trigger: -> (name, object) {
//     callbacks-for.each -> (callback) {
//       callback.run(object)
//     }
//   }
//
//   add-callback: -> (name, block) {
//     callbacks << Callback.new(name, block)
//   }
//
//   callbacks-for: -> (name) {
//     callbacks // In base class, only add events and callbacks
//   }
// }

// Stream.Accumulating: class(objects, callbacks) << Stream -> {
//   init: -> {
//     objects: List.new
//     super
//   }
//
//   init: -> (objects) {
//     objects: objects
//     init
//   }
//
//   on: -> (name, block) {
//     add-callback(name, block)
//     self
//   }
//
//   on: -> (name: name == :add, block) {
//     // handles object already in the objects
//     objects.each -> (object) { block.run(object) }
//     add-callback(name, block)
//     self
//   }
//
//   finish: -> (object) {
//     objects.freeze
//     trigger(:finish, object)
//   }
//
//   finish: -> {
//     finish(:finish)
//   }
// }
//
// Stream.Callback.class(name, block) -> {
//   delegate_to(:block, :run)
// }
//
// // ------
//
// stream = Stream.new
// stream.on(:add) -> (object) { Console.pl object } // pl == print-line, p == print
// stream << "something"

// "something"
// ------

# Fauxy - Programming Language
Fauxy is a dynamic language influenced by Ruby, JavaScript, IO and Erlang. It gets its name from the combination of faux objects and faux functional style that aim for the best programmer experience while utilizing great concurrency models.

    SpecReporter: class(description, assertion) -> {
      // default init method sets instance variables
      // `description` and `assertion`

      run: -> {
        print(assertion.run, description)
      }

      // only called if `assertion.run` is true
      print: -> (status: true, description) {
        print-status("SUCCESS", description)
      }

      // default print method
      print: -> (status, description) {
        print-status("FAILURE", description)
      }

      print-status: -> (status-message, description) {
        Print.line "[{{status-message}}]: {{description}}"
      }
    }

    Spec.Reporter.new("reporting truthiness", -> { true }).run
    // => "[SUCCESS] reporting truthiness"

## A World Without `if`
The most obvious thing about the example above is the multiple method dispatch, which is to say that there are two different methods having the same name `print`. One handle the case where something truthy is passed in, and the other handles default cases (everything else). An if statement is broken into two different methods.

Fauxy encourages simple code by pushing conditionals into argument signatures.

## Mostly Immutable
Shared state/memory is the enemy of modern concurrency, and Fauxy was born with the idea that great object-oriented code often does not mutate state.

Fauxy prevents changing state on an object. Programmers can initialize an object with data and other objects, but the state of each object remains constant through out its life.

### Except that ...
Except that Fauxy allows the accumulation of state. Fauxy has Lists and other primitive objects that can aggregate state, but don't allow other kinds of mutations.

    list = List.new
    list << 1     // adds to the end
    list << 17    // etc
    // there aren't any methods to insert in the middle though
    new_list = list.sort // not the same list!

In this example, the sorted list is not the same object as the original list, which is unchanged by the sort process. Other than accumulating items, the list can't mutate.

## Objects != Functions, but ...
Object instances can be called like functions in that you can call them: `my-instance('foo')`. This is syntactic sugar for `my-instance.run('foo')`. This kind of high-level polymorphism means that we can pass anonymous functions, or objects into another method

## Stream Processing
Currying, partial application, and piping content from one process/function to another seems like a key part of functional programming and our concurrent future. In Fauxy, I have tried to make it pretty intuitive:

    a(x) >> b(:foo, _.value) >> c(_, 'bar')

The underscore `_` character is a placeholder for incoming data allowing partial application of any function. The inverse shovel operator pipes together these partially applied functions.

## Limited Scope

Fauxy limits scope to keep code simple and performant.

### Local/Temporary Variables
While it is possible to assign local variables, those variables aren't visible inside anonymous functions:

    list = List.new

    fn = -> { list << "hello" }
    fn.run
    // raises error because list is not available

    fn-2 = -> (l) { l << "hello" }
    // it can be passed in though
    fn-2(list)
    // list now has another element

Local variables are also not available inside objects or class definitions:

    my-var = 'hello-world'

    MyClass: class -> {
      print: -> {
        Print.line my-var
        // raises error because `my-var` is out of scope
      }
    }

All this encourages building objects to share functionality and state. Local variables use the traditional `=` for assignment. Instance variables are assigned with `:` on an object.

### The Global Landscape

In the above class definitions, the `:` instance attribute assignment is used in the global space. The global space is one of the only places allowing easy instance level mutation. Class definitions are each instance attributes on the global space. It is also possible to add global level helper methods to this space, but it should be done sparingly.

### Import/Export

Because the Global landscape is a place that shouldn't be polluted, Fauxy borrows the Node.js conventions of import/export to expose and use file level data in less leaky way:

    // Exports an individual spec instance that
    // could be run by a larger runner process
    export Spec.Describe.new("My spec") -> {
      it("should assert truth") -> (s) {
        s.assert(1 == 1, "expected equal")
      }
    }

    // In another file
    spec = File.import("my-spec.fx")
    spec.run

## A Work In Progress
Not a lick of code is currently working. Samples and ideas are available in the `language-experiments` directory. Working language is in progress in other parts of this project.

### Contributing
I would love feedback. Please message me on Github or open tickets. Feel free also to fork and propose.

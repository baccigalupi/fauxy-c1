// Assignment style

Printer: Class.new -> (data-thing) {
  print: -> {
    wrap( Print.line(data-thing.to_s) )
  }

  wrap: -> (e) { e }
}

// implicit modification of the class
Printer.extend -> {
  HTML: Class.new(Printer) -> (data-thing, tag) {
    wrap: -> (e) {
      "<{{tag}}>{{e}}</{{tag}}>"
    }
  }
}

// explicit modification of the class instead of implicit
Printer: Class.new(Printer) -> {
  HTML: Class.new(Printer) -> (data-thing, tag) {
    wrap: -> (e) {
      "<{{tag}}>{{e}}</{{tag}}>"
    }
  }
}

Printer.new('hello').print // 'hello'
Printer.HTML.new('hello', 'h1').print // '<h1>hello</h1>'

// ------------------------

// EARLIER Ideas for declaring a class

// class keyword has special parse meaning
// allows the setting of the name in a consistent way
// does't have the feel of assigning though
class Printer -> (data-thing) {
  print: -> {
    wrap Print.line(data-thing.to_s)
  }

  wrap: -> (e) {
    e
  }
}

// Inheritance with nested assignment
class Printer.HTML << Printer -> (data-thing, tag) {
  wrap: -> (e) {
    "<{{tag}}>{{e}}</{{tag}}>"
  }
}

Printer.new('hello').print // 'hello'
Printer.HTML.new('hello', 'h1').print // '<h1>hello</h1>'

/// ------------------------------------------
// Assignment feels better! Even with the weird naming thing

NumberToWords: Class.new(:n) -> { }

NumberToWords: class(n) -> { }

NumberToWords(n) -> { }

// allows single inheritance, pushes towards delegation
Stream.Accumulating: Stream.inherit -> {

}

Stream.Accumulating: class(objects, callbacks) << Stream -> {
}

/*
 * Class introspection, need to know its name
 * but variables don't?
 */


Print.new.line("hello world")
// equivalent to
Print.line("hello world")


// Anonymous objects, hash like things
o = Object.new(hello: 'hello', world: 'world')
Print.line "{{o.hello}} {{o.world}}"

// Shorthand
o = O(hello: 'hello', world: 'world')
// where
O: -> { Object.new(arguments) }

// arguments available as a variable for each function/method

o = Object.new('hello', 'world')
Print.line o.options
// "('hello', 'world')"

// http://mudge.name/2014/11/26/data-structures-as-functions.html?utm_source=rubyweekly&utm_medium=email
// object() calls object run??

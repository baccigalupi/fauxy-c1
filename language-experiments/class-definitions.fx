// Ideas for declaring a class

NumberToWords: Class.new(:n) -> { }

NumberToWords: class(n) -> { }

NumberToWords(n) -> { }

// allows single inheritance, pushes towards delegation
Stream.Accumulating: Stream.inherit -> {

}

Stream.Accumulating: class(objects, callbacks) << Stream -> {
}

/*
  Methods needed for class:

  new
  inherit
  set ':'

  if a no argument signature is defined will delegate
  other calls to a new instance
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
O: -> { Object.new(arguments)}

// arguments available as a variable for each function/method

o = Object.new('hello', 'world')
Print.line o.options
// "('hello', 'world')"

// http://mudge.name/2014/11/26/data-structures-as-functions.html?utm_source=rubyweekly&utm_medium=email
// object() calls object run??

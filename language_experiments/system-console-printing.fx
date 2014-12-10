o = Object.new(hello: 'hello', world: 'world')
Print.line "{{o.hello}} {{o.world}}"

o = Object.new('hello', 'world')
Print.line o.options
// "('hello', 'world')"

/*
  Print takes any stream, default stream in System.stdout
*/

Print: Class.new -> {
  init: -> {
    init(System.stdout)
  }

  init: -> (stream) {
    stream: stream
  }

  line: -> (object) {
    stream << "{{object.to_s}}\n"
  }

  line: -> {
    line("")
  }

  message: -> (object) {
    stream << object.to_s
  }

  message: -> {
    message("")
  }
}

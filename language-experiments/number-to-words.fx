NumberToWords: class(n) -> {
  setup: -> {
    describer: Stream.Accumulating.new -> (n) {
      Hundreds.new(n).to-words
    }
  }

  to-words: -> {
    split(n)
    describer.join -> (list) { list.reverse.join(' ') }
  }

  split: -> (n: n < 1000) {
    describer << n
  }

  split: -> (n) {
    convert(n - ((n / 1000).truncate * 1000))
    convert(n / 1000)
  }
}

NumberToWords.Hundreds: class(n) -> {
  to-words: -> {
    (
      hundreds-to-words(hundreds),
      Tens.new(tens).to-words
    ).compact.join(" ")
  }

  hundreds-to-words: -> (n > 0) {
    "{{Digit.new(n).to-words}}-hundred"
  }

  hundreds-to-words: -> { nil }

  hundreds: -> {
    (n/100).truncate
  }

  tens: -> {
    n - hundreds
  }
}

NumberToWords.Tens: class(n) -> {
  to-words: -> { convert(n) }

  convert: -> (n: n < 20) {
    Teens.new(n).to-words
  }

  convert: -> (n) {
    (
      TensDigit.new(tens).to-words,
      Digit.new(ones).to-words
    ).compact.join(' ')
  }

  tens: -> {
    (n/10).truncate
  }

  ones: -> {
    n - tens
  }
}

NumberToWords.Teens -> (n) {
  convert: -> (n: 11) { 'eleven' }
  convert: -> (n: 12) { 'twelve' }
  convert: -> (n: 13) { 'thirteen' }
  convert: -> (n: 15) { 'fifteen' }
  convert: -> (n: n < 20) {
    "{{NumberConverter.Digit.new(n).to-words}}teen"
  }
}

NumberToWords.Digit: class(n) -> {
  to-words: -> { convert(n) }

  convert: -> (n: 1) { 'one' }
  convert: -> (n: 2) { 'two' }
  convert: -> (n: 3) { 'three' }
  convert: -> (n: 4) { 'four' }
  convert: -> (n: 5) { 'five' }
  convert: -> (n: 6) { 'six' }
  convert: -> (n: 7) { 'seven' }
  convert: -> (n: 8) { 'eight' }
  convert: -> (n: 9) { 'nine' }
}

NumberToWords.TensDigit: class(n) -> {
  to-words: -> { convert(n) }

  convert: -> (n: 2) { 'twenty' }
  convert: -> (n: 3) { 'thirty' }
  convert: -> (n: 4) { 'fourty' }
  convert: -> (n: 5) { 'fifty' }
  convert: -> (n: 6) { 'sixty' }
  convert: -> (n: 7) { 'seventy' }
  convert: -> (n: 8) { 'eightty' }
  convert: -> (n: 9) { 'ninety' }
}

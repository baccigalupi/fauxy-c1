Object: Class.new(nil) -> {
  empty?: native(:fxn_object_is_empty)
  nil?:   native(:fxn_object_is_nil)

  true?:  -> { !empty? }
  not:    -> { !true? }
}

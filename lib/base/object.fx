Object: Class.new -> {
  empty?: native(:fxn_object_is_empty)
  true?:  -> { !empty? }
  not:    -> { !true? }
  nil?:   native(:fxn_object_is_nil)
}

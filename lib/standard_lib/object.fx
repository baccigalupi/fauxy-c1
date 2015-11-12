Object: Class.new(Object) -> {
  /*empty?: native(:fxn_object_is_empty)*/

  true?:  -> { !empty? }
  not:    -> { !true? }
}

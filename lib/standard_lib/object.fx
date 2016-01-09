Object.extend -> {
  empty?: native(:fxi_object_is_empty)
  ?:   -> { !empty? }
  not: -> { ! ? }
}

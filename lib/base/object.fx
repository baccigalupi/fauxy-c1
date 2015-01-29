Object: Class.new -> {
  empty?: native(:fxn_object_is_empty)
  true?:  -> { !empty? }
  not:    -> { !true? }
  nil?:   native(:fxn_object_is_nil)
}

/*

{"expressions": [
{"colon_expression": {"left": {"lookup": {"type": "Class Identifier", "bit": {"STRING": "Object"}}}, "right": {"method_call": {"receiver": {"lookup": {"type": "Class Identifier", "bit": {"STRING": "Class"}}}, "message": {"lookup": {"type": "Identifier", "bit": {"STRING": "new"}}}, "method_arguments": [
{"function_definition": {"expressions": [
{"colon_expression": {"left": {"lookup": {"type": "Identifier", "bit": {"STRING": "empty?"}}}, "right": {"method_call": {"message": {"lookup": {"type": "Identifier", "bit": {"STRING": "native"}}}, "method_arguments": [
{"literal": {"class": "Symbol", "bit": {"STRING": ":fxn_objec..."}}}
]}}}},
{"colon_expression": {"left": {"lookup": {"type": "Identifier", "bit": {"STRING": "true?"}}}, "right": {"function_definition": {"expressions": [
{"method_call": {"receiver": {"lookup": {"type": "Identifier", "bit": {"STRING": "empty?"}}}, "message": {"lookup": {"type": "Identifier", "bit": {"STRING": "not"}}}}}
]}}}},
{"colon_expression": {"left": {"lookup": {"type": "Identifier", "bit": {"STRING": "not"}}}, "right": {"function_definition": {"expressions": [
{"method_call": {"receiver": {"lookup": {"type": "Identifier", "bit": {"STRING": "true?"}}}, "message": {"lookup": {"type": "Identifier", "bit": {"STRING": "not"}}}}}
]}}}},
{"colon_expression": {"left": {"lookup": {"type": "Identifier", "bit": {"STRING": "nil?"}}}, "right": {"method_call": {"message": {"lookup": {"type": "Identifier", "bit": {"STRING": "native"}}}, "method_arguments": [
{"literal": {"class": "Symbol", "bit": {"STRING": ":fxn_objec..."}}}
]}}}}
]}}
]}}}}
]}

*/

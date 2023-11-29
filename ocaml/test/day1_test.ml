let test_p1 () =
  let one = 1 in
  match one with
  | 1 -> ()
  | _ -> failwith "1 != 1"
;;

let test_p2 () =
  let two = 2 in
  match two with
  | 2 -> ()
  | _ -> failwith "2 != 2"
;;

let _ =
  let open Alcotest in
  run
    "Day1"
    [ "day 1 p1", [ test_case "p1" `Quick test_p1 ]
    ; "day 1 p2", [ test_case "p2" `Quick test_p2 ]
    ]
;;

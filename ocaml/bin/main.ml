open Reader

let () =
  let res = read None |> Day3.p2 in
  Printf.printf "%d\n" res
;;

open Reader

let () =
  let res = read None |> Day6.p2 in
  Printf.printf "%d\n" res
;;

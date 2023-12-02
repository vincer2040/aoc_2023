open Reader

let () =
  let res = read None |> Day2.p2 in
  Printf.printf "%d\n" res
;;

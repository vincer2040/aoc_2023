open Reader

let () =
  let res = read None |> Day10.p2 in
  Fmt.pr "%d\n" res
;;

open Reader

let () =
  let res = read None |> Day9.p2 in
  Fmt.pr "%d\n" res
;;

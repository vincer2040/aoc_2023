open Reader

let () =
  let res = read None |> Day18.p2 in
  Fmt.pr "%d\n" res
;;

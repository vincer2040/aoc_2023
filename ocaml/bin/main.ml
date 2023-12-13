open Reader

let () =
  let res = read None |> Day12.p2 in
  Fmt.pr "%d\n" res
;;

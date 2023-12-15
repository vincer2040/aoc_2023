open Reader

let () =
  let res = read None |> Day15.p2 in
  Fmt.pr "%d\n" res
;;

open Reader

let () =
  let res = read None |> Day14.p2 in
  Fmt.pr "%d\n" res
;;

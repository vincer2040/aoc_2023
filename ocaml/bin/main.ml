open Reader

let () =
  let res = read None |> Day11.p2 in
  Fmt.pr "%d\n" res
;;

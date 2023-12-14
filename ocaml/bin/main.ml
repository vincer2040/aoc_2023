open Reader

let () =
  let res = read None |> Day13.p1 in
  Fmt.pr "%d\n" res
;;

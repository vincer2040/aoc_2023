open Reader

let () =
  let res = read None |> Day16.p2 in
  Fmt.pr "%d\n" res
;;

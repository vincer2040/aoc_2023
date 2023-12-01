let p1 input =
  let lines =
    String.split_on_char '\n' input
    |> List.filter (fun line ->
      match line with
      | "" -> false
      | _ -> true)
  in
  let res =
    List.fold_left
      (fun acc l ->
        let chars = l |> String.to_seq |> List.of_seq in
        let first = List.find (fun ch -> '0' <= ch && ch <= '9') chars in
        let last =
          List.rev chars |> List.find (fun ch -> '0' <= ch && ch <= '9')
        in
        let combined = String.make 1 first ^ String.make 1 last in
        let num = int_of_string combined in
        acc + num)
      0
      lines
  in
  Printf.printf "%d\n" res
;;

let replace str old_sub new_sub =
  let re = Re.Posix.compile_pat old_sub in
  Re.replace_string re ~by:new_sub str
;;

let p2 input =
  let lines =
    String.split_on_char '\n' input
    |> List.filter (fun line ->
      match line with
      | "" -> false
      | _ -> true)
  in
  let res =
    List.fold_left
      (fun acc l ->
        let s1 = replace l "one" "one1one" in
        let s2 = replace s1 "two" "two2two" in
        let s3 = replace s2 "three" "three3three" in
        let s4 = replace s3 "four" "four4four" in
        let s5 = replace s4 "five" "five5five" in
        let s6 = replace s5 "six" "six6six" in
        let s7 = replace s6 "seven" "seven7seven" in
        let s8 = replace s7 "eight" "eight8eight" in
        let s = replace s8 "nine" "nine9nine" in
        let chars = s |> String.to_seq |> List.of_seq in
        let first = List.find (fun ch -> '0' <= ch && ch <= '9') chars in
        let last =
          List.rev chars |> List.find (fun ch -> '0' <= ch && ch <= '9')
        in
        let combined = String.make 1 first ^ String.make 1 last in
        let num = int_of_string combined in
        acc + num)
      0
      lines
  in
  Printf.printf "%d\n" res;
  ()
;;

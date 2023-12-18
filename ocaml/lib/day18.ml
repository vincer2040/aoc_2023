let dig instructions =
  let edges, amt_dug =
    List.fold_left
      (fun (edges, amt_dug) (dir, amt) ->
        let y, x = if List.length edges == 0 then 0, 0 else List.nth edges 0 in
        let next =
          match dir with
          | "R" -> y, x + amt
          | "U" -> y - amt, x
          | "L" -> y, x - amt
          | "D" -> y + amt, x
          | _ -> failwith "invalid dir"
        in
        let edges = next :: edges in
        let amt_dug = amt_dug + amt in
        edges, amt_dug)
      ([], 0)
      instructions
  in
  edges, amt_dug
;;

let shoelace vertices =
  let n = List.length vertices in
  let rec loop i acc =
    if i = n - 1
    then
      acc
      + ((fst (List.nth vertices i) * snd (List.hd vertices))
         - (fst (List.hd vertices) * snd (List.nth vertices i)))
    else
      loop
        (i + 1)
        (acc
         + ((fst (List.nth vertices i) * snd (List.nth vertices (i + 1)))
            - (fst (List.nth vertices (i + 1)) * snd (List.nth vertices i))))
  in
  let result = loop 0 0 in
  abs result / 2
;;

let replace str old new_sub =
  let re = Re.(compile (str old)) in
  Re.replace_string re ~by:new_sub str
;;

let split_at_index str index =
  let length = String.length str in
  if index < 0 || index > length
  then invalid_arg "Index out of bounds"
  else String.sub str 0 index, String.sub str index (length - index)
;;

let p1 input =
  let input = String.trim input in
  let instructions =
    String.split_on_char '\n' input
    |> List.map (fun line ->
      let split = String.split_on_char ' ' line in
      let dir = List.nth split 0 in
      let amt = List.nth split 1 in
      let amt = int_of_string amt in
      dir, amt)
  in
  let edges, amt_dug = dig instructions in
  let s = shoelace edges in
  let x = (amt_dug / 2) - 1 in
  let r = s - x + amt_dug in
  r
;;

let p2 input =
  let input = String.trim input in
  let instructions =
    String.split_on_char '\n' input
    |> List.map (fun line ->
      let split = String.split_on_char ' ' line in
      let hex = List.nth split 2 in
      let hex = replace hex "(" "" in
      let hex = replace hex ")" "" in
      let hex = replace hex "#" "" in
      let len = String.length hex in
      let amt_str, dir_str = split_at_index hex (len - 1) in
      let amt_str = "0x" ^ amt_str in
      let dir =
        match dir_str with
        | "0" -> "R"
        | "1" -> "D"
        | "2" -> "L"
        | "3" -> "U"
        | _ -> failwith "invalid dir"
      in
      let amt = int_of_string amt_str in
      dir, amt)
  in
  let edges, amt_dug = dig instructions in
  let s = shoelace edges in
  let x = (amt_dug / 2) - 1 in
  let r = s - x + amt_dug in
  r
;;

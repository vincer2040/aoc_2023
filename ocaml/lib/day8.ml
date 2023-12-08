module StringSet = Set.Make (String)

let split input sub =
  let re = Re.(compile (str sub)) in
  Re.split re input
;;

let replace str old new_sub =
  let re = Re.(compile (str old)) in
  Re.replace_string re ~by:new_sub str
;;

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let gcd a b =
  let rec aux a b = if b = 0 then a else aux b (a mod b) in
  if a >= 0 && b >= 0 then aux a b else invalid_arg "gcd: negative argument"
;;

let lcm a b = if a = 0 || b = 0 then 0 else abs (a * b) / gcd a b

let lcm_of_list lst =
  match lst with
  | [] -> invalid_arg "lcm_of_list: empty list"
  | x :: xs -> List.fold_left lcm x xs
;;

let rec walk graph cur_location instructions instructions_idx num_steps =
  if String.compare cur_location "ZZZ" == 0
  then num_steps
  else if instructions_idx >= String.length instructions
  then walk graph cur_location instructions 0 num_steps
  else (
    let instruction = String.get instructions instructions_idx in
    let left, right = Hashtbl.find graph cur_location in
    match instruction with
    | 'R' -> walk graph right instructions (instructions_idx + 1) (num_steps + 1)
    | 'L' -> walk graph left instructions (instructions_idx + 1) (num_steps + 1)
    | _ -> failwith "invalid instruction")
;;

let rec walk2 graph cur_location instructions instructions_idx num_steps =
  if String.ends_with cur_location ~suffix:"Z"
  then num_steps
  else if instructions_idx >= String.length instructions
  then walk2 graph cur_location instructions 0 num_steps
  else (
    let instruction = String.get instructions instructions_idx in
    let left, right = Hashtbl.find graph cur_location in
    match instruction with
    | 'L' -> walk2 graph left instructions (instructions_idx + 1) (num_steps + 1)
    | 'R' ->
      walk2 graph right instructions (instructions_idx + 1) (num_steps + 1)
    | _ -> failwith "invalid instruction")
;;

let p1 input =
  let graph = Hashtbl.create 10 in
  let split_input = split input "\n\n" in
  let instructions = List.nth split_input 0 in
  let map =
    List.nth split_input 1
    |> String.split_on_char '\n'
    |> List.filter filter_none
  in
  let parse_left_right lr =
    let tos_a = replace lr "(" "" in
    let tos_b = replace tos_a ")" "" in
    let left_right = split tos_b ", " in
    let left = List.nth left_right 0 in
    let right = List.nth left_right 1 in
    left, right
  in
  List.iter
    (fun map_item ->
      let from_to_split = split map_item " = " in
      let from = List.nth from_to_split 0 in
      let tos_string = List.nth from_to_split 1 in
      let left, right = parse_left_right tos_string in
      Hashtbl.add graph from (left, right))
    map;
  let num_steps = walk graph "AAA" instructions 0 0 in
  num_steps
;;

let p2 input =
  let graph = Hashtbl.create 10 in
  let split_input = split input "\n\n" in
  let instructions = List.nth split_input 0 in
  let map =
    List.nth split_input 1
    |> String.split_on_char '\n'
    |> List.filter filter_none
  in
  let parse_left_right lr =
    let tos_a = replace lr "(" "" in
    let tos_b = replace tos_a ")" "" in
    let left_right = split tos_b ", " in
    let left = List.nth left_right 0 in
    let right = List.nth left_right 1 in
    left, right
  in
  List.iter
    (fun map_item ->
      let from_to_split = split map_item " = " in
      let from = List.nth from_to_split 0 in
      let tos_string = List.nth from_to_split 1 in
      let left, right = parse_left_right tos_string in
      Hashtbl.add graph from (left, right))
    map;
  let starts =
    Hashtbl.fold
      (fun key _ acc ->
        if String.ends_with key ~suffix:"A" then key :: acc else acc)
      graph
      []
  in
  let t =
    List.fold_left
      (fun acc start ->
        let num_steps = walk2 graph start instructions 0 0 in
        num_steps :: acc)
      []
      starts
  in
  let res = lcm_of_list t in
  res
;;

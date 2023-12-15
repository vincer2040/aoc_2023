module IntMap = Map.Make (Int)

type label =
  | Eq of (int * string * int)
  | Minus of (int * string)
[@@deriving show]

let hash_str str =
  String.fold_left
    (fun acc ch ->
      let ascii_val = int_of_char ch in
      let m17 = (acc + ascii_val) * 17 in
      m17 mod 256)
    0
    str
;;

let hash_eq str =
  let split = String.split_on_char '=' str in
  let s = List.nth split 0 in
  let num = List.nth split 1 |> int_of_string in
  let hash = hash_str s in
  Eq (hash, s, num)
;;

let hash_minus str =
  let split = String.split_on_char '-' str in
  let s = List.nth split 0 in
  let hash = hash_str s in
  Minus (hash, s)
;;

let hash_label str =
  if String.contains str '=' then hash_eq str else hash_minus str
;;

let rec add_to_list lst (s, focal) =
  match lst with
  | [] -> [ s, focal ]
  | (cur_s, cur_focal) :: tl ->
    if String.compare cur_s s == 0
    then (s, focal) :: tl
    else (cur_s, cur_focal) :: add_to_list tl (s, focal)
;;

let add_to_map map hash =
  match hash with
  | Eq (h, s, focal) ->
    if IntMap.mem h map
    then (
      let old = IntMap.find h map in
      let new_lst = add_to_list old (s, focal) in
      IntMap.add h new_lst map)
    else IntMap.add h [ s, focal ] map
  | Minus (h, s) ->
    if IntMap.mem h map
    then (
      let old = IntMap.find h map in
      let filtered =
        List.filter
          (fun (cur_s, _) ->
            if String.compare cur_s s == 0 then false else true)
          old
      in
      if List.length filtered == 0
      then IntMap.remove h map
      else IntMap.add h filtered map)
    else map
;;

let build_map labels =
  List.fold_left
    (fun acc l ->
      let hash = hash_label l in
      add_to_map acc hash)
    IntMap.empty
    labels
;;

let p1 input =
  let input = String.trim input in
  let sum =
    String.split_on_char ',' input
    |> List.fold_left
         (fun acc str ->
           let h = hash_str str in
           acc + h)
         0
  in
  sum
;;

let p2 input =
  let input = String.trim input in
  let labels = String.split_on_char ',' input in
  let map = build_map labels in
  let res =
    IntMap.fold
      (fun key value acc ->
        let box_num = key + 1 in
        let _, list_amt =
          List.fold_left
            (fun (idx, acc) (_, focal) ->
              idx + 1, acc + (box_num * idx * focal))
            (1, 0)
            value
        in
        acc + list_amt)
      map
      0
  in
  res
;;

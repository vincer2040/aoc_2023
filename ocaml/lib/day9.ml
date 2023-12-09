module IntSet = Set.Make (Int)

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let get_nums line =
  String.split_on_char ' ' line |> List.map (fun str -> int_of_string str)
;;

let rec get_difs nums difs =
  let rec get_difs_of_cur cur d =
    match cur with
    | [] -> List.rev d
    | [ hd; sc ] -> List.rev ((sc - hd) :: d)
    | hd :: tl -> get_difs_of_cur tl ((List.nth tl 0 - hd) :: d)
  in
  let are_done lst =
    let set =
      List.fold_left (fun acc num -> IntSet.add num acc) IntSet.empty lst
    in
    if IntSet.cardinal set == 1 then true else false
  in
  let difs_of_cur = get_difs_of_cur nums [] in
  let new_difs = difs_of_cur :: difs in
  if are_done difs_of_cur then new_difs else get_difs difs_of_cur new_difs
;;

let get_num_to_add lst =
  List.fold_left
    (fun acc cur_lst ->
      let len = List.length cur_lst in
      let num_to_add = List.nth cur_lst (len - 1) in
      acc + num_to_add)
    0
    lst
;;

let get_num_to_subtract lst =
  List.fold_left
    (fun acc cur_lst ->
      let num = List.nth cur_lst 0 in
      num - acc)
    0
    lst
;;

let p1 input =
  let lines = String.split_on_char '\n' input |> List.filter filter_none in
  List.fold_left
    (fun acc line ->
      let nums = get_nums line in
      let difs = get_difs nums [] in
      let nums_len = List.length nums in
      let last_num = List.nth nums (nums_len - 1) in
      let num_to_add = get_num_to_add difs in
      acc + last_num + num_to_add)
    0
    lines
;;

let p2 input =
  let lines = String.split_on_char '\n' input |> List.filter filter_none in
  List.fold_left
    (fun acc line ->
      let nums = get_nums line in
      let first_num = List.nth nums 0 in
      let difs = get_difs nums [] in
      let num = get_num_to_subtract difs in
      acc + (first_num - num))
    0
    lines
;;

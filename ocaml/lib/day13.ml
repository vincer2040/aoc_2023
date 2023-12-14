module IntMap = Map.Make (Int)
module StringMap = Map.Make (String)

type mirror =
  | Vertical
  | Horizontal

let split input sub =
  let re = Re.(compile (str sub)) in
  Re.split re input
;;

let reverse_string str =
  String.to_seq str |> List.of_seq |> List.rev |> List.to_seq |> String.of_seq
;;

let split_at_index str idx =
  let str_len = String.length str in
  let subs_len = min idx (str_len - idx) in
  let sub1_start = idx - subs_len in
  let sub1 = String.sub str sub1_start subs_len in
  let sub2 = String.sub str idx subs_len in
  reverse_string sub1, sub2
;;

let slice_list start stop lst =
  let rec take n = function
    | [] -> []
    | hd :: tl when n > 0 -> hd :: take (n - 1) tl
    | _ :: _ -> []
  in
  let rec drop n = function
    | [] -> []
    | lst' when n > 0 -> drop (n - 1) (List.tl lst')
    | lst' -> lst'
  in
  take (stop - start + 1) (drop start lst)
;;

let split_list_at_index lst idx =
  let len = List.length lst in
  let slices_len = min idx (len - idx) in
  let slice1_start = idx - slices_len in
  let slice1 = slice_list slice1_start (idx - 1) lst |> List.rev in
  let slice2 = slice_list idx (idx + slices_len - 1) lst in
  slice1, slice2
;;

let get_num_difs str1 str2 =
  let _, res =
    String.fold_left
      (fun (idx, acc) ch1 ->
        let ch2 = String.get str2 idx in
        if ch1 == ch2 then idx + 1, acc else idx + 1, acc + 1)
      (0, 0)
      str1
  in
  res
;;

let is_horizontal_mirror pattern idx is_p2 =
  let len = List.length pattern in
  if idx <= 0 || idx >= len
  then false
  else (
    let slice1, slice2 = split_list_at_index pattern idx in
    if is_p2
    then (
      let slice1, slice2 = split_list_at_index pattern idx in
      let calc_num_difs (idx, acc) s1 =
        let s2 = List.nth slice2 idx in
        let num_difs = get_num_difs s1 s2 in
        idx + 1, acc + num_difs
      in
      let _, num_difs = List.fold_left calc_num_difs (0, 0) slice1 in
      if num_difs == 1 then true else false)
    else if List.compare String.compare slice1 slice2 == 0
    then true
    else false)
;;

let find_vertical_mirrors pattern exp_difs =
  let line_len = List.nth pattern 0 |> String.length in
  let l = List.init (line_len - 1) (fun i -> i + 1) in
  let find (found, idx) i =
    if found
    then found, idx
    else (
      let create_subs p = split_at_index p i in
      let calc_num_difs acc (sub1, sub2) = acc + get_num_difs sub1 sub2 in
      let subs = List.map create_subs pattern in
      let num_difs = List.fold_left calc_num_difs 0 subs in
      if num_difs == exp_difs then true, i else found, idx)
  in
  let res = List.fold_left find (false, 0) l in
  res
;;

let find_horizontal_mirrors pattern ~is_p2 =
  let len = List.length pattern in
  let l = List.init len (fun i -> i) in
  let find (found, idx) i =
    if found
    then found, idx
    else if is_horizontal_mirror pattern i is_p2
    then true, i
    else found, idx
  in
  let found, idx = List.fold_left find (false, 0) l in
  found, idx
;;

let get_idx pattern ~num_difs ~is_p2 =
  let split = String.split_on_char '\n' pattern in
  let found_horiz, idx = find_vertical_mirrors split num_difs in
  if found_horiz
  then Horizontal, idx
  else (
    let found_vert, idx = find_horizontal_mirrors split ~is_p2 in
    if found_vert then Vertical, idx else Horizontal, 0)
;;

let p1 input =
  let add acc p =
    let m, idx = get_idx p ~num_difs:0 ~is_p2:false in
    match m with
    | Horizontal -> acc + idx
    | Vertical -> acc + (idx * 100)
  in
  let input = String.trim input in
  let patterns = split input "\n\n" in
  let res = List.fold_left add 0 patterns in
  res
;;

let p2 input =
  let add acc p =
    let m, idx = get_idx p ~num_difs:1 ~is_p2:true in
    match m with
    | Horizontal -> acc + idx
    | Vertical -> acc + (idx * 100)
  in
  let input = String.trim input in
  let patterns = split input "\n\n" in
  let res = List.fold_left add 0 patterns in
  res
;;

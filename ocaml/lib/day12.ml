let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let create_data_item line =
  let split = String.split_on_char ' ' line in
  let springs = List.nth split 0 in
  let nums =
    List.nth split 1
    |> String.split_on_char ','
    |> List.map (fun num -> int_of_string num)
  in
  springs, nums
;;

let rec num_combos (springs, nums) i bi current map =
  let key = i, bi, current in
  if Hashtbl.mem map key
  then Hashtbl.find map key
  else if i == String.length springs
  then
    if bi == List.length nums && current = 0
    then 1
    else if bi == List.length nums - 1 && List.nth nums bi == current
    then 1
    else 0
  else (
    let c = [ '.'; '#' ] in
    let ans =
      List.fold_left
        (fun acc ch ->
          if String.get springs i == ch || String.get springs i == '?'
          then
            if ch == '.' && current == 0
            then acc + num_combos (springs, nums) (i + 1) bi 0 map
            else if ch == '.'
                    && current > 0
                    && bi < List.length nums
                    && List.nth nums bi == current
            then acc + num_combos (springs, nums) (i + 1) (bi + 1) 0 map
            else if ch == '#'
            then acc + num_combos (springs, nums) (i + 1) bi (current + 1) map
            else acc
          else acc)
        0
        c
    in
    Hashtbl.add map key ans;
    ans)
;;

let p1 input =
  let get_result acc line =
    let map = Hashtbl.create 10 in
    let data = create_data_item line in
    acc + num_combos data 0 0 0 map
  in
  let res =
    String.split_on_char '\n' input
    |> List.filter filter_none
    |> List.fold_left get_result 0
  in
  res
;;

let p2 input =
  let get_result acc line =
    let map = Hashtbl.create 10 in
    let springs0, nums0 = create_data_item line in
    let q = String.make 1 '?' in
    let springs =
      springs0 ^ q ^ springs0 ^ q ^ springs0 ^ q ^ springs0 ^ q ^ springs0
    in
    let nums = nums0 @ nums0 @ nums0 @ nums0 @ nums0 in
    acc + num_combos (springs, nums) 0 0 0 map
  in
  let res =
    String.split_on_char '\n' input
    |> List.filter filter_none
    |> List.fold_left get_result 0
  in
  res
;;

type seed =
  { start : int
  ; length : int
  }

type range =
  { dst : int
  ; src : int
  ; range : int
  }

type map_item =
  { from : string
  ; to_s : string
  ; map : range list
  }

let print_map_item map_item =
  Printf.printf "from: %s to %s\n" map_item.from map_item.to_s;
  List.iter
    (fun range ->
      Printf.printf
        "dst: %d src: %d range: %d\n"
        range.dst
        range.src
        range.range)
    map_item.map
;;

let rec slice list idx =
  match list with
  | [] -> []
  | _ :: tail -> if idx - 1 == 0 then tail else slice tail (idx - 1)
;;

let replace str old new_sub =
  let re = Re.Posix.compile_pat old in
  Re.replace_string re ~by:new_sub str
;;

let split input sub =
  let re = Re.(compile (str sub)) in
  Re.split re input
;;

let find_smallest lst =
  match lst with
  | [] -> 0
  | hd :: tl -> List.fold_left (fun min_num x -> min min_num x) hd tl
;;

let p1 input =
  let full = split input "\n\n" in
  let seeds =
    replace (List.nth full 0) "seeds: " ""
    |> String.split_on_char ' '
    |> List.map (fun s -> int_of_string s)
  in
  let maps = slice full 1 in
  let get_nums numbers_string =
    String.split_on_char ' ' numbers_string
    |> List.map (fun s -> int_of_string s)
  in
  let get_new_seed (is_done, seed) check =
    if is_done
    then is_done, seed
    else (
      let dst = List.nth check 0 in
      let src = List.nth check 1 in
      let range = List.nth check 2 in
      if seed >= src && seed <= src + range
      then true, seed + (dst - src)
      else false, seed)
  in
  let find_seed acc chunk =
    let nums =
      slice (String.split_on_char '\n' chunk) 1
      |> List.filter (fun s ->
        match s with
        | "" -> false
        | _ -> true)
      |> List.map get_nums
    in
    let _, new_seed = List.fold_left get_new_seed (false, acc) nums in
    new_seed
  in
  let get_end_vals acc seed =
    let new_seed = List.fold_left find_seed seed maps in
    new_seed :: acc
  in
  let end_vals = List.fold_left get_end_vals [] seeds in
  let smallest = find_smallest end_vals in
  smallest
;;

let rec create_seeds seeds seed_values =
  match seed_values with
  | [] -> List.rev seeds
  | f :: s :: tl ->
    let seed = { start = f; length = s } in
    create_seeds (seed :: seeds) tl
  | _ -> List.rev seeds
;;

let filter_empty s =
  match s with
  | "" -> false
  | _ -> true
;;

let max_of_three a b c = max a (max b c)

let rec insert_at_index index element lst =
  match lst with
  | [] when index = 0 -> [ element ]
  | [] -> failwith "Index out of bounds"
  | _hd :: _tl when index = 0 -> element :: lst
  | hd :: tl -> hd :: insert_at_index (index - 1) element tl
;;

let rec walk value range name map =
  try
    let item = Hashtbl.find map name in
    try
      let range_item =
        List.find
          (fun x ->
            match x with
            | x when x.src <= value && value < x.src + x.range -> true
            | _ -> false)
          item.map
      in
      let dif = value - range_item.src in
      let new_value = range_item.dst + dif in
      let min_range = min range (range_item.range - dif) in
      walk new_value min_range item.to_s map
    with
    | Not_found -> walk value 1 item.to_s map
  with
  | Not_found -> value, range
;;

let p2 input =
  let table = Hashtbl.create 10 in
  let full = split input "\n\n" in
  let seed_values =
    replace (List.nth full 0) "seeds: " ""
    |> String.split_on_char ' '
    |> List.map (fun s -> int_of_string s)
  in
  let seeds = create_seeds [] seed_values in
  let map_strs = slice full 1 in
  let get_vals l =
    let to_ints =
      String.split_on_char ' ' l
      |> List.filter filter_empty
      |> List.map (fun s -> int_of_string s)
    in
    let dst = List.nth to_ints 0 in
    let src = List.nth to_ints 1 in
    let range = List.nth to_ints 2 in
    { dst; src; range }
  in
  let generate_map_items lst l =
    let split = String.split_on_char '\n' l |> List.filter filter_empty in
    let from_to_str = List.nth split 0 in
    let from_to_split =
      String.split_on_char
        '-'
        (List.nth (String.split_on_char ' ' from_to_str) 0)
    in
    let from = List.nth from_to_split 0 in
    let to_s = List.nth from_to_split 2 in
    let data = slice split 1 in
    let vals = List.map get_vals data in
    let map_item_val = { from; to_s; map = vals } in
    map_item_val :: lst
  in
  let map_items = List.fold_left generate_map_items [] map_strs in
  let rec insert_negatives start acc = function
    | [] -> List.rev_append acc [ { src = start; dst = start; range = 0 } ]
    | range :: rest ->
      if range.src > start
      then (
        let new_range =
          { src = start; dst = start; range = range.src - start }
        in
        insert_negatives
          (range.src + range.range)
          (new_range :: range :: acc)
          rest)
      else insert_negatives (range.src + range.range) (range :: acc) rest
  in
  let create_negative_map_ranges m_item =
    let sorted_ranges = List.sort (fun a b -> a.src - b.src) m_item.map in
    let new_ranges = insert_negatives 0 [] sorted_ranges in
    { m_item with map = new_ranges }
  in
  let negative_map_ranges =
    List.map create_negative_map_ranges (List.rev map_items)
  in
  List.iter
    (fun map_item -> Hashtbl.add table map_item.from map_item)
    negative_map_ranges;
  let lowest =
    List.fold_left
      (fun min_val seed ->
        let remaining = seed.length in
        let start = seed.start in
        let rec get_new_low s r lowest =
          if r <= 0
          then lowest
          else (
            let start_location, consumed = walk s r "seed" table in
            let new_remaining = r - consumed in
            let new_start = s + consumed in
            let new_lowest = min start_location lowest in
            get_new_low new_start new_remaining new_lowest)
        in
        let new_min = get_new_low start remaining min_val in
        new_min)
      Int.max_int
      seeds
  in
  lowest
;;

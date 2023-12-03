type dir =
  { dy : int
  ; dx : int
  }

type pos =
  { y : int
  ; x : int
  }

type num =
  { num : int
  ; positions : pos list
  }

let dirs =
  [ { dy = 0; dx = -1 }
  ; (* left *)
    { dy = 0; dx = 1 }
  ; (* right *)
    { dy = -1; dx = -1 }
  ; (* up left *)
    { dy = -1; dx = 0 }
  ; (* up *)
    { dy = -1; dx = 1 }
  ; (* up right *)
    { dy = 1; dx = -1 }
  ; (* down left *)
    { dy = 1; dx = 0 }
  ; (* down *)
    { dy = 1; dx = 1 } (* down right *)
  ]
;;

let rec create_row line len idx init =
  if idx == len
  then List.rev init
  else create_row line len (idx + 1) (String.get line idx :: init)
;;

let make_matrix input =
  let lines = String.split_on_char '\n' input in
  List.map
    (fun l ->
      let len = String.length l in
      create_row l len 0 [])
    lines
;;

let print_matrix matrix =
  List.iter
    (fun row ->
      List.iter (fun ch -> Printf.printf "%c " ch) row;
      Printf.printf "\n")
    matrix
;;

let print_pos pos = Printf.printf "pos: (y: %d, x: %d) " pos.y pos.x

let print_num num =
  Printf.printf "%d " num.num;
  List.iter (fun pos -> print_pos pos) num.positions
;;

let is_num ch =
  match ch with
  | ch when '0' <= ch && ch <= '9' -> true
  | _ -> false
;;

let is_symbol ch =
  if is_num ch then false else if ch == '.' then false else true
;;

let is_gear ch = if ch == '*' then true else false

let rec parse_num row row_len row_idx idx num =
  if idx >= row_len
  then { num with positions = List.rev num.positions }, idx
  else (
    let cur = List.nth row idx in
    if is_num cur
    then (
      let cur_char = List.nth row idx in
      let new_num_val = (num.num * 10) + (int_of_char cur_char - 48) in
      let pos = { y = row_idx; x = idx } in
      let new_num = { num = new_num_val; positions = pos :: num.positions } in
      parse_num row row_len row_idx (idx + 1) new_num)
    else { num with positions = List.rev num.positions }, idx)
;;

let rec parse_nums row row_len row_idx idx nums =
  if idx >= row_len
  then List.rev nums
  else if is_num (List.nth row idx)
  then (
    let num, new_idx =
      parse_num row row_len row_idx idx { num = 0; positions = [] }
    in
    parse_nums row row_len row_idx (new_idx + 1) (num :: nums))
  else parse_nums row row_len row_idx (idx + 1) nums
;;

let rec parse_symbols row row_len row_idx idx positions =
  if idx >= row_len
  then List.rev positions
  else (
    let cur = List.nth row idx in
    if is_symbol cur
    then (
      let pos = { y = row_idx; x = idx } in
      parse_symbols row row_len row_idx (idx + 1) (pos :: positions))
    else parse_symbols row row_len row_idx (idx + 1) positions)
;;

let rec parse_gears row row_len row_idx idx positions =
  if idx >= row_len
  then List.rev positions
  else (
    let cur = List.nth row idx in
    if is_gear cur
    then (
      let pos = { y = row_idx; x = idx } in
      parse_gears row row_len row_idx (idx + 1) (pos :: positions))
    else parse_gears row row_len row_idx (idx + 1) positions)
;;

let is_valid num symbol_positions =
  let positions = num.positions in
  List.fold_left
    (fun acc pos ->
      try
        let _ =
          List.find
            (fun dir ->
              let y = pos.y + dir.dy in
              let x = pos.x + dir.dx in
              List.mem { y; x } symbol_positions)
            dirs
        in
        true
      with
      | Not_found -> acc)
    false
    positions
;;

let rec traverse matrix cur len sum =
  if cur == len
  then sum
  else (
    let prev_row_symbols =
      match cur with
      | 0 -> []
      | _ ->
        let prev = List.nth matrix (cur - 1) in
        parse_symbols prev (List.length prev) (cur - 1) 0 []
    in
    let next_row_symbols =
      match cur with
      | cur when cur < len - 1 ->
        let next = List.nth matrix (cur + 1) in
        parse_symbols next (List.length next) (cur + 1) 0 []
      | _ -> []
    in
    let cur_row = List.nth matrix cur in
    let cur_row_symbols =
      parse_symbols cur_row (List.length cur_row) cur 0 []
    in
    let symbol_positions =
      prev_row_symbols @ cur_row_symbols @ next_row_symbols
    in
    let nums = parse_nums cur_row (List.length cur_row) cur 0 [] in
    let t =
      List.fold_left
        (fun acc num ->
          if is_valid num symbol_positions then acc + num.num else acc)
        0
        nums
    in
    traverse matrix (cur + 1) len (sum + t))
;;

let rec traverse2 matrix cur len map =
  if cur == len
  then map
  else (
    let prev_row_gears =
      match cur with
      | 0 -> []
      | _ ->
        let prev = List.nth matrix (cur - 1) in
        parse_gears prev (List.length prev) (cur - 1) 0 []
    in
    let next_row_gears =
      match cur with
      | cur when cur < len - 1 ->
        let next = List.nth matrix (cur + 1) in
        parse_gears next (List.length next) (cur + 1) 0 []
      | _ -> []
    in
    let cur_row = List.nth matrix cur in
    let cur_row_symbols = parse_gears cur_row (List.length cur_row) cur 0 [] in
    let gear_positions = prev_row_gears @ cur_row_symbols @ next_row_gears in
    let nums = parse_nums cur_row (List.length cur_row) cur 0 [] in
    List.iter
      (fun gp ->
        List.iter
          (fun num ->
            let positions = num.positions in
            try
              let _ =
                List.find
                  (fun pos ->
                    List.fold_left
                      (fun acc dir ->
                        let p = { y = pos.y + dir.dy; x = pos.x + dir.dx } in
                        if p.y == gp.y && p.x == gp.x then true else acc)
                      false
                      dirs)
                  positions
              in
              if Hashtbl.mem map gp
              then (
                let l = Hashtbl.find map gp in
                Hashtbl.replace map gp (num.num :: l))
              else Hashtbl.add map gp [ num.num ]
            with
            | Not_found -> ())
          nums)
      gear_positions;
    traverse2 matrix (cur + 1) len map)
;;

let p1 input =
  let matrix = make_matrix input in
  let res = traverse matrix 0 (List.length matrix) 0 in
  res
;;

let p2 input =
  let matrix = make_matrix input in
  let new_map = Hashtbl.create 10 in
  let map = traverse2 matrix 0 (List.length matrix) new_map in
  Hashtbl.fold
    (fun _ value acc ->
      if List.length value == 2
      then (
        let v1 = List.nth value 0 in
        let v2 = List.nth value 1 in
        acc + (v1 * v2))
      else acc)
    map
    0
;;

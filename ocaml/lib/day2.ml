type color =
  | Blue of int
  | Red of int
  | Green of int

type game_totals =
  { blue : int list
  ; red : int list
  ; green : int list
  }

let init_color string num =
  match string with
  | "blue" -> Blue num
  | "red" -> Red num
  | "green" -> Green num
  | _ -> failwith "invalid color"
;;

let init_game_total () = { blue = []; red = []; green = [] }

let add_color color game_total =
  match color with
  | Blue num -> { game_total with blue = num :: game_total.blue }
  | Red num -> { game_total with red = num :: game_total.red }
  | Green num -> { game_total with green = num :: game_total.green }
;;

let find_max lst =
  match lst with
  | [] -> failwith "empty list"
  | hd :: tl -> List.fold_left max hd tl
;;

let get_total game_total =
  let blue_amt = find_max game_total.blue in
  let red_amt = find_max game_total.red in
  let green_amt = find_max game_total.green in
  blue_amt * red_amt * green_amt
;;

let print_color color =
  match color with
  | Green num -> Printf.printf "green %d\n" num
  | Red num -> Printf.printf "red %d\n" num
  | Blue num -> Printf.printf "blue %d\n" num
;;

let is_possible color =
  match color with
  | Green num when num <= 13 -> true
  | Red num when num <= 12 -> true
  | Blue num when num <= 14 -> true
  | _ -> false
;;

let p1 input =
  let res =
    String.split_on_char '\n' input
    |> List.filter (fun line ->
      match line with
      | "" -> false
      | _ -> true)
    |> List.fold_left
         (fun acc line ->
           let split = String.split_on_char ':' line in
           let game_id =
             List.nth (String.split_on_char ' ' (List.nth split 0)) 1
             |> int_of_string
           in
           let set_strs = List.nth split 1 |> String.split_on_char ';' in
           let games =
             List.fold_left
               (fun acc set ->
                 let game = String.split_on_char ',' set in
                 let games =
                   List.fold_left
                     (fun acc g ->
                       let trimmed = String.trim g in
                       let split_trimmed = String.split_on_char ' ' trimmed in
                       let num = List.nth split_trimmed 0 |> int_of_string in
                       let color_str = List.nth split_trimmed 1 in
                       let color = init_color color_str num in
                       color :: acc)
                     []
                     game
                 in
                 games :: acc)
               []
               set_strs
           in
           let flat = List.flatten games in
           let possible =
             List.fold_left
               (fun acc cur -> if is_possible cur then acc else false)
               true
               flat
           in
           if possible then acc + game_id else acc)
         0
  in
  res
;;

let p2 input =
  let res =
    String.split_on_char '\n' input
    |> List.filter (fun line ->
      match line with
      | "" -> false
      | _ -> true)
    |> List.fold_left
         (fun acc line ->
           let split = String.split_on_char ':' line in
           let set_strs = List.nth split 1 |> String.split_on_char ';' in
           let games =
             List.fold_left
               (fun acc set ->
                 let game = String.split_on_char ',' set in
                 let games =
                   List.fold_left
                     (fun acc g ->
                       let trimmed = String.trim g in
                       let split_trimmed = String.split_on_char ' ' trimmed in
                       let num = List.nth split_trimmed 0 |> int_of_string in
                       let color_str = List.nth split_trimmed 1 in
                       let color = init_color color_str num in
                       color :: acc)
                     []
                     game
                 in
                 games :: acc)
               []
               set_strs
           in
           let totals_record =
             List.flatten games
             |> List.fold_left (fun acc g -> add_color g acc)
                @@ init_game_total ()
           in
           acc + get_total totals_record)
         0
  in
  res
;;

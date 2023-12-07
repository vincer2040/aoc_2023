type hand_result =
  | FiveOfAKind
  | FourOfAKind
  | FullHouse
  | ThreeOfAKind
  | TwoPair
  | OnePair
  | HighCard
[@@deriving show, ord, eq]

let hand_result_to_int hand_result =
  match hand_result with
  | FiveOfAKind -> 6
  | FourOfAKind -> 5
  | FullHouse -> 4
  | ThreeOfAKind -> 3
  | TwoPair -> 2
  | OnePair -> 1
  | HighCard -> 0
;;

let to_ordered_string hand =
  String.fold_left
    (fun acc ch ->
      let next =
        match ch with
        | 'A' -> 'z'
        | 'K' -> 'y'
        | 'Q' -> 'x'
        | 'J' -> 'w'
        | 'T' -> 'v'
        | '9' -> 'u'
        | '8' -> 't'
        | '7' -> 's'
        | '6' -> 'r'
        | '5' -> 'q'
        | '4' -> 'p'
        | '3' -> 'o'
        | '2' -> 'n'
        | '1' -> 'm'
        | _ -> failwith "invalid card"
      in
      acc ^ String.make 1 next)
    ""
    hand
;;

let to_ordered_string2 hand =
  String.fold_left
    (fun acc ch ->
      let next =
        match ch with
        | 'A' -> 'z'
        | 'K' -> 'y'
        | 'Q' -> 'x'
        | 'T' -> 'w'
        | '9' -> 'v'
        | '8' -> 'u'
        | '7' -> 't'
        | '6' -> 's'
        | '5' -> 'r'
        | '4' -> 'q'
        | '3' -> 'p'
        | '2' -> 'o'
        | '1' -> 'n'
        | 'J' -> 'm'
        | _ -> failwith "invalid card"
      in
      acc ^ String.make 1 next)
    ""
    hand
;;

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let calculate_hand hand =
  let map = Hashtbl.create 10 in
  String.iter
    (fun ch ->
      if Hashtbl.mem map ch
      then (
        let old_amt = Hashtbl.find map ch in
        let new_amt = old_amt + 1 in
        Hashtbl.replace map ch new_amt)
      else Hashtbl.add map ch 1)
    hand;
  let result =
    Hashtbl.fold
      (fun _ value acc ->
        match value with
        | 1 -> acc
        | 2 ->
          (match acc with
           | HighCard -> OnePair
           | OnePair -> TwoPair
           | ThreeOfAKind -> FullHouse
           | _ -> failwith "invalid hand")
        | 3 ->
          (match acc with
           | HighCard -> ThreeOfAKind
           | OnePair -> FullHouse
           | _ -> failwith "invalid hand")
        | 4 -> FourOfAKind
        | 5 -> FiveOfAKind
        | _ -> failwith "invalid value")
      map
      HighCard
  in
  result
;;

let calculate_hand2 hand =
  let map = Hashtbl.create 10 in
  String.iter
    (fun ch ->
      if Hashtbl.mem map ch
      then (
        let old_amt = Hashtbl.find map ch in
        let new_amt = old_amt + 1 in
        Hashtbl.replace map ch new_amt)
      else Hashtbl.add map ch 1)
    hand;
  let result =
    Hashtbl.fold
      (fun _ value acc ->
        match value with
        | 1 -> acc
        | 2 ->
          (match acc with
           | HighCard -> OnePair
           | OnePair -> TwoPair
           | ThreeOfAKind -> FullHouse
           | _ -> failwith "invalid hand")
        | 3 ->
          (match acc with
           | HighCard -> ThreeOfAKind
           | OnePair -> FullHouse
           | _ -> failwith "invalid hand")
        | 4 -> FourOfAKind
        | 5 -> FiveOfAKind
        | _ -> failwith "invalid value")
      map
      HighCard
  in
  let new_result =
    match result with
    | HighCard -> if Hashtbl.mem map 'J' then OnePair else result
    | OnePair -> if Hashtbl.mem map 'J' then ThreeOfAKind else result
    | TwoPair ->
      if Hashtbl.mem map 'J'
      then (
        let amt_j = Hashtbl.find map 'J' in
        match amt_j with
        | 1 -> FullHouse
        | 2 -> FourOfAKind
        | _ -> failwith "invalid hand")
      else result
    | ThreeOfAKind -> if Hashtbl.mem map 'J' then FourOfAKind else result
    | FullHouse -> if Hashtbl.mem map 'J' then FiveOfAKind else result
    | FourOfAKind -> if Hashtbl.mem map 'J' then FiveOfAKind else result
    | _ -> result
  in
  new_result
;;

let p1 input =
  let hands_bids =
    String.split_on_char '\n' input
    |> List.filter filter_none
    |> List.map (fun line ->
      let split = String.split_on_char ' ' line in
      let hand = List.nth split 0 in
      let bid = List.nth split 1 |> int_of_string in
      hand, bid)
  in
  let calculated =
    List.fold_left
      (fun acc (hand, bid) ->
        let hand_result = calculate_hand hand in
        (hand_result, hand, bid) :: acc)
      []
      hands_bids
    |> List.rev
  in
  let compare (ares, ahand, _) (bres, bhand, _) =
    if ares != bres
    then hand_result_to_int ares - hand_result_to_int bres
    else (
      let ordered_a = to_ordered_string ahand in
      let ordered_b = to_ordered_string bhand in
      String.compare ordered_a ordered_b)
  in
  let sorted =
    List.sort compare calculated |> List.mapi (fun i (_, _, bid) -> i + 1, bid)
  in
  let result = List.fold_left (fun acc (i, bid) -> acc + (i * bid)) 0 sorted in
  result
;;

let p2 input =
  let hands_bids =
    String.split_on_char '\n' input
    |> List.filter filter_none
    |> List.map (fun line ->
      let split = String.split_on_char ' ' line in
      let hand = List.nth split 0 in
      let bid = List.nth split 1 |> int_of_string in
      hand, bid)
  in
  let calculated =
    List.fold_left
      (fun acc (hand, bid) ->
        let hand_result = calculate_hand2 hand in
        (hand_result, hand, bid) :: acc)
      []
      hands_bids
    |> List.rev
  in
  let compare (ares, ahand, _) (bres, bhand, _) =
    if ares != bres
    then hand_result_to_int ares - hand_result_to_int bres
    else (
      let ordered_a = to_ordered_string2 ahand in
      let ordered_b = to_ordered_string2 bhand in
      String.compare ordered_a ordered_b)
  in
  let sorted =
    List.sort compare calculated |> List.mapi (fun i (_, _, bid) -> i + 1, bid)
  in
  let result = List.fold_left (fun acc (i, bid) -> acc + (i * bid)) 0 sorted in
  result
;;

//
//  PokemonViewController.swift
//  Pokedex
//
//  Created by Melvin Kok on 29/12/20.
//

import UIKit

class PokemonViewController : UIViewController {
    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    var pokemon: Pokemon!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        nameLabel.text = pokemon.name
//        numberLabel.text = String(format: "#%03d", pokemon.number)
    }
}

import {gql} from '@apollo/client'

export const GET_DATA = gql`
query getUser($id: ID){
    getUser(id: $id) {
        Value
    }
}     
`
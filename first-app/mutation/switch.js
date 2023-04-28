import {gql} from '@apollo/client'

export const UPDATE_STATE = gql`
    mutation updateState($id: Int, $Enabled: Boolean) {
        updateState(id: $id, Enabled: $Enabled) {
            id, Enabled
        }
    }
`